# PHP Cookies, Sessions, AND Session Variables

Cookies can only be written as part of header information, therefore cannot
create or add to a cookie after writing to browser.

Create a cookie: `setcookie(cookiename, value, [expire]);`.

Retrieved: `$_COOKIE['cookiename']`.

Delete a cookie: `setcookie("cook", “”， time()-100);`.

Create a session: `session_start()`.

Retrieved: `$_SESSION`.

Get Session ID: `session_id()`.

Erase all session variables and data: `session_unset()`.

Erase a single variable and data: `unset($_SESSION['myvar'])`.

Destroys the session data without destroying the session variables:
`session_destroy()`.

