It's possible to reuse a SSL socket after proper cleanup.

See [SSL Socket free and shutdown](https://stackoverflow.com/questions/21193743/ssl-socket-free-and-shutdown) on stackoverflow.

SSL_shutdown only sends an close notify over the socket. If you want to reuse the socket afterwards as a plain socket you have to make sure, that the other side did also an SSL_shutdown. This information gives you the return code of your SSL_shutdown: if it is 1 the SSL connection is closed, if it is 0 you should call SSL_shutdown again so wait for the close notify from the peer. Please see the SSL_shutdown documentation for more information.

After this is done you can continue to use the socket as a plain socket. This what is done in SSL over FTP (ftps), e.g. with "AUTH TLS" the connection will be upgraded to SSL and with "CCC" it will be downgraded to plain text again.

SSL_free only frees the memory associated with the SSL object, it does not change anything on the socket nor does it send/receive any data.
