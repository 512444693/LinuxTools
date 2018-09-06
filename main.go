package main

import (
	"bytes"
	"encoding/json"
	"errors"
	"flag"
	"fmt"
	"io"
	"io/ioutil"
	"log"
	"mime/multipart"
	"net/http"
	"os"
	"os/exec"
)

// GetTokenURL 获取token的url
const GetTokenURL string = "https://qyapi.weixin.qq.com/cgi-bin/gettoken?corpid=%s&corpsecret=%s"

// MessageSendURL 发送消息的url
const MessageSendURL string = "https://qyapi.weixin.qq.com/cgi-bin/message/send?access_token=%s"

// UploadURL 上传文件的url(现在固定为图片)
const UploadURL string = "https://qyapi.weixin.qq.com/cgi-bin/media/upload?access_token=%s&type=image"

var token string

func getToken() (string, error) {
	resp, err := http.Get(fmt.Sprintf(GetTokenURL, CORPID, SECRET))
	if err != nil {
		return "", err
	}
	defer resp.Body.Close()

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		return "", err
	}

	gtr := &getTokenResp{}
	err = json.Unmarshal(body, gtr)
	if err != nil {
		return "", err
	}

	if gtr.ErrCode != 0 {
		return "", fmt.Errorf("%d: %s", gtr.ErrCode, gtr.ErrMsg)
	}
	return gtr.AccessToken, nil
}

func send(token string, content []byte) error {
	resp, err := http.Post(fmt.Sprintf(MessageSendURL, token), "application/json", bytes.NewReader(content))
	if err != nil {
		return err
	}
	defer resp.Body.Close()

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		return err
	}
	smr := &sendMsgResp{}
	err = json.Unmarshal(body, smr)
	if err != nil {
		return err
	}
	if smr.ErrCode != 0 {
		return errors.New(smr.ErrMsg)
	}
	return nil
}

func sendText(token string, msg string) error {
	sm := &sendMsg{
		MsgType: "text",
		// ToParty: TOPARTY,
		ToUser:  TOUSER,
		AgentID: AGENTID,
		Safe:    0,
		Text: content{
			Content: msg,
		},
	}
	b, err := json.Marshal(sm)
	if err != nil {
		return err
	}

	return send(token, b)
}

func uploadFile(token, file string) (mediaID string, err error) {
	buf := &bytes.Buffer{}
	w := multipart.NewWriter(buf)
	fw, err := w.CreateFormFile("media", file)

	f, err := os.Open(file)
	if err != nil {
		return "", err
	}
	_, err = io.Copy(fw, f)
	if err != nil {
		return "", err
	}
	w.Close()

	resp, err := http.Post(fmt.Sprintf(UploadURL, token), w.FormDataContentType(), buf)
	if err != nil {
		return "", err
	}
	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		return "", err
	}
	ur := &uploadResp{}
	err = json.Unmarshal(body, ur)
	if err != nil {
		return "", err
	}
	if ur.ErrCode == 0 {
		return ur.MediaID, nil
	}
	return "", errors.New(ur.ErrMsg)
}

func sendImage(token string, file string) error {
	mediaID, err := uploadFile(token, file)
	if err != nil {
		return err
	}

	sm := &sendMsg{
		MsgType: "image",
		// ToParty: TOPARTY,
		ToUser:  TOUSER,
		AgentID: AGENTID,
		Safe:    0,
		Image: media{
			MediaID: mediaID,
		},
	}
	b, err := json.Marshal(sm)
	if err != nil {
		return err
	}
	log.Println("send image ok")

	return send(token, b)
}

func wx(w http.ResponseWriter, r *http.Request) {
	r.ParseForm()
	msgs := r.Form["msg"]
	if len(msgs) == 0 || msgs[0] == "" {
		w.WriteHeader(http.StatusBadRequest)
		w.Write([]byte("no msg set"))
		return
	}
	log.Printf("rec wx action: %s\r\n", msgs[0])
	err := sendText(token, msgs[0])
	if err != nil { // 如果错误，可能是token过期，再重试一次
		token, err = getToken()
		if err != nil {
			w.WriteHeader(http.StatusInternalServerError)
			w.Write([]byte(err.Error()))
			return
		}
		err = sendText(token, msgs[0])
		if err != nil {
			w.WriteHeader(http.StatusInternalServerError)
			w.Write([]byte(err.Error()))
			return
		}
	}
	w.Write([]byte("send message ok"))
}

func takePictrue(file string) error {
	cmd := exec.Command("raspistill", "-w", "640", "-h", "480", "-t", "1000", "-o", file)
	return cmd.Run()
}

func tp(w http.ResponseWriter, r *http.Request) {
	log.Println("rec tp action")
	file := "cam.jpg"
	err := takePictrue(file)
	if err != nil {
		w.WriteHeader(http.StatusInternalServerError)
		w.Write([]byte(err.Error()))
	}
	err = sendImage(token, file)
	if err != nil { // 如果错误，可能是token过期，再重试一次
		token, err = getToken()
		if err != nil {
			w.WriteHeader(http.StatusInternalServerError)
			w.Write([]byte(err.Error()))
			return
		}
		err = sendImage(token, file)
		if err != nil {
			w.WriteHeader(http.StatusInternalServerError)
			w.Write([]byte(err.Error()))
			return
		}
	}
	w.Write([]byte("send image ok"))
}

func main() {
	port := flag.String("p", ":9090", "port to listen")
	flag.Parse()

	// 程序启动时，获取一次token
	t, err := getToken()
	if err != nil {
		log.Println(err)
		return
	}
	token = t
	log.Println("get token ok")

	http.HandleFunc("/wx", wx)
	http.HandleFunc("/tp", tp)
	log.Println("listen: ", *port)
	log.Println(http.ListenAndServe(*port, nil))
}
