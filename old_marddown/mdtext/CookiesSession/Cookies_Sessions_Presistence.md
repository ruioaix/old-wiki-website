# Cookies, Sessions, and Persistence

HTTP is stateless, sessions and cookies make it stateful.

Sessions are used and stored by server.

the problem with Sessions is that the sessions are always tied to connections,
the time-out time of connection is set by http server, for example, apache,
usually 5 seconds; a session in Apache will remain in memory for 300 seconds.

Cookies are used and stored on the client by the browser.

the cookies for any given domain are always passed to the server by the
browser in the HTTP headers.

Almost all modern web applications generate a "session ID" and pass it along
as a cookie, this means: server can find the right session on the server even
after the connection from which the session was created is closed.

the problem with Sessions and Cookies is that it is possible for the same user
to have each request made to an application be distributed to a different
server because of load balancing techniques, and the session on one server is
rarely shared with other servers.

Persistence is a technique implemented by Application Delivery Controllers
that ensures requests from a single user are always distributed to the server
on which they started.

