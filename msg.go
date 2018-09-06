package main

type getTokenResp struct {
	ErrCode     int    `json:"errcode"`
	ErrMsg      string `json:"errmsg"`
	AccessToken string `json:"access_token"`
	ExpiresIn   int    `json:"expires_in"`
}

type content struct {
	Content string `json:"content"`
}
type media struct {
	MediaID string `json:"media_id"`
}
type sendMsg struct {
	ToUser  string  `json:"touser"`
	ToParty string  `json:"toparty"`
	MsgType string  `json:"msgtype"`
	AgentID int     `json:"agentid"`
	Safe    int     `json:"safe"`
	Text    content `json:"text"`
	Image   media   `json:"image"`
}

type sendMsgResp struct {
	ErrCode int    `json:"errcode"`
	ErrMsg  string `json:"errmsg"`
}

type uploadResp struct {
	ErrCode int    `json:"errcode"`
	ErrMsg  string `json:"errmsg"`
	MediaID string `json:"media_id"`
}
