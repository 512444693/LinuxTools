/**
 *    @file       httpreply.cpp
 *
 *    @brief      
 *    @details    
 *
 *    @version    1.0
 *    @date       2015/4/25
 *
 *    @author     zhangjiaxing, zhangjiaxing@baofeng.com
 */
#include "httpreply.h"

string ToString(int status)
{
	switch (status)
	{
	case OK:
		return str_ok;
	case CREATED:
		return str_created;
	case ACCEPTED:
		return str_accepted;
	case NP_CONTENT:
		return str_no_content;
	case MULTIPLE_CHOICES:
		return str_multiple_choices;
	case MOVED_PERMANENTLY:
		return str_moved_permanently;
	case MOVED_TEMPORARILY:
		return str_moved_temporarily;
	case NOT_MODIFIED:
		return str_not_modified;
	case BAD_REQUEST:
		return str_bad_request;
	case UNAUTHORIZED:
		return str_unauthorized;
	case FORBIDDEN:
		return str_forbidden;
	case NOT_FOUND:
		return str_not_found;
	case METHOD_NOT_ALLOWED:
		return str_method_not_allowed;
	case INTERNAL_SERVER_ERROR:
		return str_internal_server_error;
	case NOT_INPLEMENTED:
		return str_not_implemented;
	case BAD_GATEWAY:
		return str_bad_gateway;
	case SERVICE_UNAVAILABLE:
		return str_service_unavailable;
	case GATEWAY_TIMEOUT:
		return str_gateway_timeout;
	default:
		return str_internal_server_error;
	}
}


