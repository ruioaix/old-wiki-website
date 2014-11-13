# Cookies and Sessions Maintaining State in HTTP

First, browser request a web page, then server sends page+cookie, then maybe,
browser request another web page, but this time, browser will send the request
and cookies back to server.

Cookies are marked as to the web addresses they come from, the browser only
sends back cookies that were originally set by the same web server.

Cookies have an expiration date, some last for years, some go away as soon as
the browser is closed.

The cookies which servers send to browser first time is with a sessionID.

The creation and destruction of sessions is generally handled by a web
framework or some utility code that we just use to manage the sessions.

Shopping cart or login information is stored in the session in the server.

Server software stores sessions somewhere, each time a request comes back in,
the right session is retrieved based on the cookie.

