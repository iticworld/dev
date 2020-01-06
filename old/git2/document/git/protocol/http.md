__DOCUMENTATION__

# HTTP TRANSFER PROTOCOLS

Git supports two HTTP based transfer protocols.
A dumb protocol which requires only a standard HTTP server on the server end of the connection, and smart protocol requires a Git aware CGI (or server module).
This document describes both protocols.

As a design feature smart clients can automatically upgrade dumb protocol URLs to smart URLs.
This permits all users to have the same published URL, and the peers automatically select the most efficient transport available to them.

## URL FORMAT

URLs for Git repositories accessed by HTTP use the standard HTTP URL syntax documented by [RFC 1738](https://www.ietf.org/rfc/rfc1738.txt), so they are of the form:

    http://<host>:<port>/<path>?<search part>
    
Within this documentation the placeholder '_$GIT_URL_' will stand for the _http://_ repository URL entered by the end user.  

Servers should handle all requests to locations matching '_$GIT_URL_', as by appending additional path components onto the end of the user supplied '_$GIT_URL_' string.

An example of a dumb client requesting for a loose object:

    $GIT_URL:     http://example.com:8080/git/repo.git
    URL request:  http://example.com:8080/git/repo.git/objects/d0/49f6c27a2244e12041955e262a404c7faba355
    
An example of a smart request to a catch-all gateway:

    $GIT_URL:     http://example.com/daemon.cgi?svc=git&q=
    URL request:  http://example.com/daemon.cgi?svc=git&q=/info/refs&service=git-receive-pack

An example of a request to a submodule:

    $GIT_URL:     http://example.com/git/repo.git/path/submodule.git
    URL request:  http://example.com/git/repo.git/path/submodule.git/info/refs
    
Clients must strip a trailing '/', if present, from the user supplied '_$GIT_URL_' string to prevent empty path tokens ('//') from appearing in any URL sent to a server.
Compatible clients must expand '_$GIT_URL/info/refs_' as '_foo/info/refs_' and not '_foo//info/refs_'.

## AUTHENTICATION

Standard HTTP authentication is used if authentication is required to access a repository, and may be configured and enforced by the HTTP server software.

Because git repositories are accessed by standard path components server administrators may use directory based permissions within their HTTP server to control repository access.

Clients should support basic authentication as described by [RFC 2617](https://www.ietf.org/rfc/rfc2617.txt).
Servers should support basic authentication by relying upon the HTTP server placed in front of the git server software.

Servers should not require HTTP cookies for the purpose of authentication or access control.

Clients and servers may support other common forms of HTTP based authentication, such as Digest authentication.

## SSL

Clients and servers should support SSL, particularly to protect passwords when relying on basic HTTP authentication.

## SESSION STATE

The Git over HTTP protocol (much like HTTP itself) is stateless from the perspective of the HTTP server side.
All state must be retained and managed by the client process.
This permits simple round-robin load-balancing on the server side, without needing to worry about state management.

Clients must not require state management on the server side in order to function correctly.

Servers must not require HTTP cookies in order to function correctly.
Clients may store and forward HTTP cookies during request processing as described by [RFC 2616](https://www.ietf.org/rfc/rfc2616.txt).
Servers should ignore any cookies sent by a client.

## GENERAL REQUEST PROCESSING

Except where noted, all standard HTTP behavior should be assumed by both client and server.
This includes (but is not necessarily limited to):

If there is no repository at '_$GIT_URL_', or the resource pointed to by a location matching '_$GIT_URL_' does not exists, the server must response with '_200 OK_' response.
A server should respond with '_404 Not Found_', '_410 Gone_', or any other suitable HTTP status code which doest not imply the resource exists as requested.

If there is a repository at '_$GIT_URL_', but access is not currently permitted, the server must respond with the '_403 Forbidden_' HTTP status code.

Servers should support both HTTP 1.0 and HTTP 1.1.

Servers should chunked encoding for both request and response bodies.

Clients should support both HTTP 1.0 and HTTP 1.1.

Clients should support chunked encoding for both request and response bodies.

Servers may return ETag and/or Last-Modified headers.

Clients may revalidate cached entities by including If-Modified-Since If-None-Match request headers.

Servers may return '_304 Not Modified_' if the relevant headers appear in the request and the entity has not changed.
Client must treat '_304 Not Modified_' identical to '_200 OK_' by reusing the cached entity.

Clients may reuse a cached entity without revalidation if the Cache-Control and/or Expires header permits caching. Clients and servers must follow [RFC 2616](https://www.ietf.org/rfc/rfc2616.txt) for cache controls.

## DISCOVERING REFERENCES

All HTTP clients must begin either a fetch or a push exchange by discovering the references available on the remote repository.

### DUMB CLIENTS

HTTP clients that only support the dumb protocol must discover references by making a request for the special info/refs file of the repository.

Dumb HTTP clients must make a '_GET_' request to '_$GIT_URL/info/refs_', without any search/query parameters.

    C: GET $GIT_URL/info/refs HTTP/1.0
    S: 200 OK
    S: 
    S: 95dcfa3633004da0049d3d0fa03f80589cbcaf31	refs/heads/maint
    S: d049f6c27a2244e12041955e262a404c7faba355	refs/heads/master
    S: 2cb58b79488a98d2721cea644875a8dd0026b115	refs/tags/v1.0
    S: a3c2e2402b99163d1d59756e5f207ae21cccba4c	refs/tags/v1.0^{}
    
The Content-Type of the returned info/refs entity should be '_text/plain; charset=urf-8_', but may be any content type.
Clients must not attempt to validate the returned Content-Type.
Dumb servers must not return a return type starting with '_application/x-git-_'.

Cache-Control headers may be returned to disable caching of the returned entity.

When examining the response clients should only examine the HTTP status code.
Valid responses are '_200 OK_', or '_304 Not Modified_'.

The returned content is a unix formatted text file describing each ref and its known value.
The file should be sorted by name according to the C locale ordering.
The file should not include the default ref named '_HEAD_'.

    info_refs   =  *(ref_record)
    ref_record  = any_ref/peeled_ref
    
    any_ref     = obj-id HTAB refname LF
    peeled_ref  = obj-id HTAB refname LF
    obj-id HTAB refname "^{}" LF

### SMART CLIENTS

HTTP clients that support the smart protocol (or both the smart and dumb protocols) must discover references by making a parameterized request for the info/refs file of the repository.

The request must contain exactly one query parameter, '_service=$servicename_', where '_$servicename_' must be the service name the client wishes to contact to complete the operation.
The request must not contain additional query parameters.

    C: GET $GIT_URL/info/refs?service=git-upload-pack HTTP/1.0
    
dumb server reply:

    S: 200 OK
    S:
    S: 95dcfa3633004da0049d3d0fa03f80589cbcaf31	refs/heads/maint
    S: d049f6c27a2244e12041955e262a404c7faba355	refs/heads/master
    S: 2cb58b79488a98d2721cea644875a8dd0026b115	refs/tags/v1.0
    S: a3c2e2402b99163d1d59756e5f207ae21cccba4c	refs/tags/v1.0^{}

smart server reply:

    S: 200 OK
    S: Content-Type: application/x-git-upload-pack-advertisement
    S: Cache-Control: no-cache
    S:
    S: 001e# service=git-upload-pack\n
    S: 0000
    S: 004895dcfa3633004da0049d3d0fa03f80589cbcaf31 refs/heads/maint\0multi_ack\n
    S: 0042d049f6c27a2244e12041955e262a404c7faba355 refs/heads/master\n
    S: 003c2cb58b79488a98d2721cea644875a8dd0026b115 refs/tags/v1.0\n
    S: 003fa3c2e2402b99163d1d59756e5f207ae21cccba4c refs/tags/v1.0^{}\n
    S: 0000

The client may send Extra Parameter [packfile transfer protocol](packfile.transfer.md) as a colon-separated string in the Git-Protocol HTTP header.

#### DUMB SERVER RESPONSE

Dumb servers must respond with the dumb server reply format.

See the prior section under dumb clients for a more detailed description of the dumb server response.

#### SMART SERVER RESPONSE

If the server does not recognize the requested service name, or the request service name has been disabled by the server administrator, the server must respond with the '_403 Forbidden_' HTTP status code.

Otherwise, smart servers must respond with the smart server reply format for the requested service name.

Cache-Control headers should be used to disable caching of the returned entity.

The Content-Type must be '_application/x-$servicename-advertisement_'.
Clients should fall back to the dumb protocol if another content type is returned.
When falling back to the dumb protocol clients should not make an additional request to '_$GIT_URL/info/refs_', but instead should use the response already in hand.
Clients must not continue if they do not support the dumb protocol.

Clients must validate the status code is either '_200 OK_' or '_304 Not Modified_'.

Clients must validate the first five bytes of the response entity matches the regex '_^\[0-9a-f\]{4}#_'.
If this test fails, client must not continue.

Clients must parse the entire response as a sequence of _pkt-line_ records.

Clients must verify the first _pkt-line_ is '_# service=$servicename_'.
Servers must set _$servicename_ to be the request parameter value.
Servers should include an LF at the end of this line.
Clients must ignore an LF at the end of the line.

Servers must terminate the response with the magic '_0000_' end _pkt-line marker.

The returned response is a _pkt-line_ stream describing each ref and its known value.
The stream should be stored by name according to the C locale ordering.
The stream include the default ref named '_HEAD_' as the first ref.
The stream must include capability declarations behind a _NUL_ no the first ref.

The returned response contains "_version 1_" if "_version=1_" was sent as an extra parameter.

    smart_reply     =  PKT-LINE("# service=$servicename" LF)
    "0000"
    *1("version 1")
    ref_list
    "0000"
    ref_list        = empty_list/non_empty_list
    empty_list      = PKT_LINE(zero-id SP "capabilities^{}" NUL cap-list LF)
    non_empty_list  = PKT-LINE(obj-id SP name NUL cap_list LF)
    *ref_record
    
    cap-list        = capability *(SP capability)
    capability      = 1*(LC_ALPHA/DIGIT/"-"/"_")
    LC_ALPHA        = %x61-7A
    ref_record      = any_ref/peeled_ref
    any_ref         = PKT-LINE(obj-id SP name LF)
    peeled_ref      = PKT-LINE(obj-id SP name LF)
                      PKT-LINE(obj-id SP name "^{}" LF

## SMART SERVICE GIT-UPLOAD-PACK

This service reads from the repository pointed to by '_$GIT_URL_'.

Clients must first perform ref discovery with '_$GIT_URL/info/refs?service=git-upload-pack_'.

    C: POST $GIT_URL/git-upload-pack HTTP/1.0
    C:
    C: 0032want 0a53e9ddeaddad63ad106860237bbf53411d11a7\n
    C: 0032have 441b40d833fdfa93eb2908e52742248faf0ee993\n
    C: 0000
    
    S: 200 OK
    S: Content-Type: application/x-git-upload-pack-result
    S: Cache-Control: no-cache
    S:
    S: ....ACK %s, continue
    S: ....NAK
    
Clients must not reuse or revalidate a cached response.
Servers must include sufficient Cache-Control headers to prevent caching of the response.

Servers should support all capabilities defined here.





    Servers SHOULD support all capabilities defined here.

    Clients MUST send at least one "want" command in the request body.
    Clients MUST NOT reference an id in a "want" command which did not
appear in the response obtained through ref discovery unless the
server advertises capability `allow-tip-sha1-in-want` or
    `allow-reachable-sha1-in-want`.

    compute_request   =  want_list
have_list
request_end
request_end       =  "0000" / "done"

want_list         =  PKT-LINE(want SP cap_list LF)
*(want_pkt)
want_pkt          =  PKT-LINE(want LF)
want              =  "want" SP id
cap_list          =  capability *(SP capability)

have_list         =  *PKT-LINE("have" SP id LF)

TODO: Document this further.

    The Negotiation Algorithm
~~~~~~~~~~~~~~~~~~~~~~~~~
    The computation to select the minimal pack proceeds as follows
(C = client, S = server):

'init step:'

C: Use ref discovery to obtain the advertised refs.

    C: Place any object seen into set `advertised`.

    C: Build an empty set, `common`, to hold the objects that are later
determined to be on both ends.

    C: Build a set, `want`, of the objects from `advertised` the client
wants to fetch, based on what it saw during ref discovery.

    C: Start a queue, `c_pending`, ordered by commit time (popping newest
first).  Add all client refs.  When a commit is popped from
the queue its parents SHOULD be automatically inserted back.
    Commits MUST only enter the queue once.

'one compute step:'

C: Send one `$GIT_URL/git-upload-pack` request:

    C: 0032want <want #1>...............................
C: 0032want <want #2>...............................
....
C: 0032have <common #1>.............................
C: 0032have <common #2>.............................
....
C: 0032have <have #1>...............................
C: 0032have <have #2>...............................
....
C: 0000

The stream is organized into "commands", with each command
appearing by itself in a pkt-line.  Within a command line,
    the text leading up to the first space is the command name,
    and the remainder of the line to the first LF is the value.
    Command lines are terminated with an LF as the last byte of
the pkt-line value.

    Commands MUST appear in the following order, if they appear
at all in the request stream:

    * "want"
* "have"

The stream is terminated by a pkt-line flush (`0000`).

    A single "want" or "have" command MUST have one hex formatted
SHA-1 as its value.  Multiple SHA-1s MUST be sent by sending
multiple commands.

    The `have` list is created by popping the first 32 commits
from `c_pending`.  Less can be supplied if `c_pending` empties.

    If the client has sent 256 "have" commits and has not yet
received one of those back from `s_common`, or the client has
emptied `c_pending` it SHOULD include a "done" command to let
    the server know it won't proceed:

C: 0009done

S: Parse the git-upload-pack request:

    Verify all objects in `want` are directly reachable from refs.

    The server MAY walk backwards through history or through
the reflog to permit slightly stale requests.

    If no "want" objects are received, send an error:
    TODO: Define error if no "want" lines are requested.

    If any "want" object is not reachable, send an error:
    TODO: Define error if an invalid "want" is requested.

    Create an empty list, `s_common`.

    If "have" was sent:

    Loop through the objects in the order supplied by the client.

    For each object, if the server has the object reachable from
a ref, add it to `s_common`.  If a commit is added to `s_common`,
    do not add any ancestors, even if they also appear in `have`.

    S: Send the git-upload-pack response:

    If the server has found a closed set of objects to pack or the
request ends with "done", it replies with the pack.
    TODO: Document the pack based response

S: PACK...

The returned stream is the side-band-64k protocol supported
by the git-upload-pack service, and the pack is embedded into
stream 1.  Progress messages from the server side MAY appear
in stream 2.

Here a "closed set of objects" is defined to have at least
one path from every "want" to at least one "common" object.

    If the server needs more information, it replies with a
    status continue response:
TODO: Document the non-pack response

C: Parse the upload-pack response:
    TODO: Document parsing response

'Do another compute step.'


Smart Service git-receive-pack
------------------------------
    This service reads from the repository pointed to by `$GIT_URL`.

    Clients MUST first perform ref discovery with
    `$GIT_URL/info/refs?service=git-receive-pack`.

        C: POST $GIT_URL/git-receive-pack HTTP/1.0
C: Content-Type: application/x-git-receive-pack-request
C:
    C: ....0a53e9ddeaddad63ad106860237bbf53411d11a7 441b40d833fdfa93eb2908e52742248faf0ee993 refs/heads/maint\0 report-status
C: 0000
C: PACK....

S: 200 OK
S: Content-Type: application/x-git-receive-pack-result
S: Cache-Control: no-cache
S:
    S: ....

Clients MUST NOT reuse or revalidate a cached response.
    Servers MUST include sufficient Cache-Control headers
to prevent caching of the response.

    Servers SHOULD support all capabilities defined here.

    Clients MUST send at least one command in the request body.
    Within the command portion of the request body clients SHOULD send
the id obtained through ref discovery as old_id.

    update_request  =  command_list
"PACK" <binary data>

command_list    =  PKT-LINE(command NUL cap_list LF)
*(command_pkt)
command_pkt     =  PKT-LINE(command LF)
cap_list        =  *(SP capability) SP

command         =  create / delete / update
create          =  zero-id SP new_id SP name
delete          =  old_id SP zero-id SP name
update          =  old_id SP new_id SP name

TODO: Document this further.


    References
----------

    http://www.ietf.org/rfc/rfc1738.txt[RFC 1738: Uniform Resource Locators (URL)]
http://www.ietf.org/rfc/rfc2616.txt[RFC 2616: Hypertext Transfer Protocol -- HTTP/1.1]
    link:technical/pack-protocol.html
link:technical/protocol-capabilities.html