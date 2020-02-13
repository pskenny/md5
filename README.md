# MD5
MD5 hash algorithm implementation.

[From MD5 RFC 1321]
The  algorithm takes as input a message of arbitrary length and produces as output a 128-bit "fingerprint" or "message digest" of the input. It is conjectured that it is computationally infeasible to produce two messages having the same message digest, or to produce any message having a given prespecified target message digest. The MD5 algorithm is intended for digital signature applications, where a large file must be "compressed" in a secure manner before being encrypted with a private (secret) key under a public-key cryptosystem such as RSA.

## Getting Started

This is a guide to getting this project up and running from source.

### Prerequisites

- GCC
- Autotools

E.g. On Debian-based distributions:

```bash
> sudo apt install gcc autotools
```

### Installation

1. Clone repo

```bash
> git clone https://github.com/pskenny/md5
> cd md5
```

2. Set up an m4 environment

```bash
> aclocal
```

3. Generate configure file fron configure.ac

```bash
> autoconf
```

4. Generate Makefile.in from Makefile.am

```bash
> automake --add-missing
```

5. Generate Makefile from Makefile.in

```bash
> ./configure
```

6. Build project

```bash
> make
```

7. Install

```bash
> make install
```

## Resources

- Theory Of Algorithms module course work (including documents, videos and lectures) provided by [Ian McLoughlin](https://github.com/ianmcloughlin/).
- [The magic behind configure, make, make install](https://thoughtbot.com/blog/the-magic-behind-configure-make-make-install). How to use autotools for easier project build, distribution and installation.
