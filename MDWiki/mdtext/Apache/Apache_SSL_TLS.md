# Apache SSL/TLS Encryption

在RHEL6上使用yum安装的apache是没有ssl支持的，使用`yum install mod_ssl`可以得到ssl，并且通过在
_/etc/httpd/conf.d/_ 下放置ssl.conf文件自动使能ssl，监听443端口。

## 一些HTTPS中会用到的概念

  * cryptographic algorithms包括两种：对称加密，非对称加密。 
  * Message Digests：散列算法，或者叫hash算法。可以提取任意文件的DNA。 
  * Digital Signatures：就是使用非对称加密中的私钥对文件的DNA以及其他一些信息进行加密之后的输出。 

## certificate（证书）

certificate 的内容

  * subject：public key和特定的身份特征。 
  * issuer：CA的身份特征和CA的数字签名。 
  * 证书有效期 

CA（certificate authorities）可以为其他的CA发行证书，所以在验证证书的时候，就可能需要验证这个证书的CA，以及这个证书的CA的CA
，……直到遇到了一个浏览器内置的可信任的CA。

如上，所说，总有一个最顶层的CA，这个CA没有人授予其自己的证书，所以，其是“self-signed”的，所有顶级的CA都是“self-
signed”的，这些顶级的CA自己的证书中，subject和issuer是一样的。

浏览器总是预先内置了一些可信任的顶级CA的“self-signed”的证书。

## 思考一些网络验证的情况

情况：alice想让银行给她邮寄一些钱，alice是银行的贵宾，其帐号有个几亿的，所以alice只需要把自己家的地址告诉银行，银行就会立即邮寄钱过去。当然这
是在银行确定是alice本人的情况下。

  1. alice不希望除了银行之外的人知道自己家的地址，所以，通过网络明文发送自己家的地址是不行的，有两个问题： 
    * 可能会被网络监听。 
    * 如何确认对方就是银行。 
  2. 通过使用银行的public key，可以保证被监听也无所谓，对方不是银行也无所谓，只有真正的银行才能获取alice的信息。 
  3. 但新的问题是，任何人都可以有银行的public key，所以，网络上的人可能拦下alice的信息，然后将自己的地址用public key加密，然后发给一行。 
  4. 所以alice，将自己的地址加密之后，hash出了一个值，将两者都传给银行；如果网络上的xx只将alice的地址换成自己的，那么银行在hash验证的时候，就会出错，就不干了。 
    * 但是，这个网络上的xx，连同hash值一起换成自己的了，这样银行验证的时候也不会出错。 
  5. 于是alice又做了一件事：将hash值用自己的private key加密，然后同加密后的地址，两个一起传出去。 
    * 网络上的xx傻了，即使拦截了两个，也没用，因为他没有alice的private key，他无法伪造使用alice private key加密的东西。 
  6. 到这里为止，网络上的xx，没戏了。但是，alice还是没收到钱，为啥呢，因为她使用的所谓的银行的public key，其实不是银行的。是网络上的yy的。 
  7. 网络上的yy是网络上的xx的祖师～，yy拦截了alice的家庭地址之后，直接用自己的private key破解了，虽然没办法做进一步的事情（因为alice的private key 加密的hash，他也没办法伪造），但是alice还是泄漏了家庭地址，并且没收到需要的钱。 
  8. 为此，alice斥责了银行，“丫的，你们xxxxxx”，银行没办法，赶紧去CA那里办了个证书，这样，alice每次先从银行的网站上得到证书，然后CA会验证下证书，证书正确的话，就可以得到银行的public key了，正确的public key了。 

## Apache Certificates

有几个文件会存在于server端：

  * RSA private key file，用来解密的；public key是放在certificate里面的。 
  * Certificates Signing Request（CSR），server用来交给CA，从而CA可以sign这个，然后给server一个真正的certificate。 
  * certificate，包含了server的public key，server的名字，CA的名字，CA的sign。client获得这个证书，CA解密这个证书，就得到了server的public key。 

CA会用自己的private
key加密其所签发的certificate。所以，CA验证的过程应该是，从certificate找到对应的CA，然后得到CA的public
key，然后解密certificate，大概吧。

在apache的httpd.conf中与ssl相关的directive：

  * `SSLCertificateFile /path/to/this/server.crt`
  * `SSLCertificateKeyFile /path/to/this/server.key`

## 建立self-signed的certificate和private key

  * `openssl genrsa -out server.key 1024`
  * `openssl req -new -x509 -nodes -sha1 -days 365 -key server.key -out server.crt`

观察两者配对情况：

  * `openssl x509 -noout -modulus -in server.crt | openssl md5`
  * `openssl rsa -noout -modulus -in server.key | openssl md5`

使用self-signed的Certificates来签发其他的证书。

  * `openssl req -newkey rsa:1024 -nodes -out ourdomain.csr -keyout ourdomain.key`
  * `openssl ca -batch -config /path/to/myca.conf -notext -in req.csr -out /path/to/ourdomain.cer`

