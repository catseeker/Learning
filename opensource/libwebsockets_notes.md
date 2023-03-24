# libwebsockets using notes

### 1. Getting http header during upgrade connection

#### 1.1 Getting url arg of http request

##### 1.1.1 lws callback option
(1) LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION 

(2) description:
called when the handshake has been received and parsed from the client, but the response is not sent yet. Return non-zero to disallow the connection. user is a pointer to the connection user space allocation, in is the requested protocol name In your handler you can use the public APIs lws_hdr_total_length() / lws_hdr_copy() to access all of the headers using the header enums lws_token_indexes from libwebsockets.h to check for and read the supported header presence and content before deciding to allow the handshake to proceed or to kill the connection.

##### 1.1.2 lws api function
(1) lws_get_urlarg_by_name_safe() / lws_get_urlarg_by_name()

(2) description:
lws_get_urlarg_by_name_safe() - get copy and return length of y for x=y urlargs

Parameters
wsi	the connection to check
name	the arg name, like "token" or "token="
buf	the buffer to receive the urlarg (including the name= part)
len	the length of the buffer to receive the urlarg
Returns -1 if not present, else the length of y in the urlarg name=y. If zero or greater, then buf contains a copy of the string y. Any = after the name match is trimmed off if the name does not end with = itself.

This returns the explicit length and so can deal with binary blobs that are percent-encoded. It also makes sure buf has a NUL just after the valid length so it can work with NUL-based apis if you don't care about truncation.

buf may have been written even when -1 is returned indicating no match.

Use this in place of lws_get_urlarg_by_name() that does not return an explicit length.

#### 2.Getting http header options of request

##### 2.1 lws callback option
(1) LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION 

##### 2.2 lws api function
(1) lws_hdr_copy()
 
(2) description:
 lws_hdr_copy() - copy all fragments of the given header to a buffer The buffer length len must include space for an additional terminating '\0', or it will fail returning -1.

Parameters
wsi	websocket connection
dest	destination buffer
len	length of destination buffer
h	which header index we are interested in
copies the whole, aggregated header, even if it was delivered in several actual headers piece by piece. Returns -1 or length of the whole header.

(3) Example:
int result [0,65]
lws_hdr_copy() gets value -> no-cache
lws_token_to_string() gets profile -> pragma:

### 3. lws send by callback
#### 3.1 lws api function
(1) /**
 * lws_callback_on_writable_all_protocol() - Request a callback for all
 *			connections using the given protocol when it
 *			becomes possible to write to each socket without
 *			blocking in turn.
 *
 * \param context:	lws_context
 * \param protocol:	Protocol whose connections will get callbacks
 *
 * - Which:  connections using this protocol on ANY VHOST
 * - When:   when the individual connection becomes writeable
 * - What: LWS_CALLBACK_*_WRITEABLE
 */
LWS_VISIBLE LWS_EXTERN int
lws_callback_on_writable_all_protocol(const struct lws_context *context,
				      const struct lws_protocols *protocol);
### 4. lws get uri
#### 4.1 lws api function:
lws_http_get_uri_and_method(wsi, &uri, &uriLen)

#### 4.2 example:
http://127.0.0.1:7681/event/getPostion?version=1.0&encrypt=tls1.2&token=12345

api gets uri -> /event/getPostion
