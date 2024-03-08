#include <spider.h>

ssl_t* OpenSSL_initializer(int sock)
{
    /*1. 创建ssl_t*/
    ssl_t* ssl = NULL;
    if ((ssl = (ssl_t*)malloc(sizeof(ssl_t))) == NULL)
    {
        perror("openssl initializer, malloc failed");
        exit(0);
    }
    // 初始化错误处理
    SSL_load_error_strings();
    // 初始化openssl库
    SSL_library_init();
    // 初始化散列函数
    OpenSSL_add_ssl_algorithms();
    // 初始化SSL_XTX，将兼容性较强的版本信息赋值
    ssl->sslctx = SSL_CTX_new(SSLv23_method());
    // 创建安全套接字
    ssl->sslsock = SSL_new(ssl->sslctx);

    // 设置使用tcpsock设置安全套接字
    SSL_set_fd(ssl->sslsock, sock);

    // 发起认证，完成认证过程
    SSL_connect(ssl->sslsock);

    return ssl;
    // SSL_read(ssl->sock) 读取并解密  SSL_write(lll->sock) 加密并发送
}