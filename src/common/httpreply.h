/**
 *    @file       httpreply.h
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2015/4/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
 
#ifndef __HTTP_REPLY_H_
#define __HTTP_REPLY_H_

#include "framecommon/framecommon.h"
#include <string>
#include "HttpRecvAndSendTask.h"
#include <vector>
using namespace std;

///the http content type
#define HTTP_CONTENT_TYPE "text/html"
#define HTTP_CONTENT_TYPE_JSON "application/json"
#define HTTP_COMMON_CONNECT_TYPE_CLOSE "close"
#define HTTP_COMMON_CONNECT_KEEP_ALIVE "keep-alive"

///gen http head
#define GEN_NEW_HTTP_RET_HEAD(sHTTPHEAD, sContentLen, sContentType, sGMTTime) \
	(sHTTPHEAD\
	+ "Content-Length: " + sContentLen + HTTP_LIND_END\
	+ "Content-Type: " + sContentType + HTTP_LIND_END\
	+ "Access-Control-Allow-Origin: *" + HTTP_LIND_END\
	+ "Server: nginx/1.6.1" + HTTP_LIND_END\
	+ "Date: " + sGMTTime + HTTP_LIND_END\
	+ "X-Powered-By: PHP/5.4.31" + HTTP_LIND_END\
	+ "Connection: " + HTTP_COMMON_CONNECT_KEEP_ALIVE + HTTP_HEAD_END);

///the status of the reply
enum
{
	OK = 200,
	CREATED = 201,
	ACCEPTED = 202,
	NP_CONTENT = 204,
	MULTIPLE_CHOICES = 300,
	MOVED_PERMANENTLY = 301,
	MOVED_TEMPORARILY = 302,
	NOT_MODIFIED = 304,
	BAD_REQUEST = 400,
	UNAUTHORIZED = 401,
	FORBIDDEN = 403,
	NOT_FOUND = 404,
	METHOD_NOT_ALLOWED = 405,
	INTERNAL_SERVER_ERROR = 500,
	NOT_INPLEMENTED = 501,
	BAD_GATEWAY = 502,
	SERVICE_UNAVAILABLE = 503,
	GATEWAY_TIMEOUT = 504
};

///the string of the reply
const string str_ok = "HTTP/1.1 200 OK\r\n";
const string str_created = "HTTP/1.1 201 Created\r\n";
const string str_accepted = "HTTP/1.0 202 Accepted\r\n";
const string str_no_content = "HTTP/1.1 204 No Content\r\n";
const string str_multiple_choices = "HTTP/1.1 300 Multiple Choices\r\n";
const string str_moved_permanently = "HTTP/1.1 301 Moved Permanently\r\n";
const string str_moved_temporarily = "HTTP/1.1 302 Moved Temporarily\r\n";
const string str_not_modified = "HTTP/1.1 304 Not Modified\r\n";
const string str_bad_request = "HTTP/1.1 400 Bad Request\r\n";
const string str_unauthorized = "HTTP/1.1 401 Unauthorized\r\n";
const string str_forbidden = "HTTP/1.1 403 Forbidden\r\n";
const string str_not_found = "HTTP/1.1 404 Not Found\r\n";
const string str_method_not_allowed = "HTTP/1.1 405 Method Not Allowed\r\n";
const string str_internal_server_error = "HTTP/1.1 500 Internal Server Error\r\n";
const string str_not_implemented = "HTTP/1.1 501 Not Implemented\r\n";
const string str_bad_gateway = "HTTP/1.1 502 Bad Gateway\r\n";
const string str_service_unavailable = "HTTP/1.1 503 Service Unavailable\r\n";
const string str_gateway_timeout = "HTTP/1.1 504 Gateway Timeout\r\n";

/**
* @brief get string of status
* @param[in] reply status
* @return string of status
*/
string ToString(int status);
#endif


