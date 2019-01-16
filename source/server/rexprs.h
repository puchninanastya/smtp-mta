#ifndef SMTP_MTA_REXPRS_H
#define SMTP_MTA_REXPRS_H

/* COMMON: */

#define RE_CRLF "\\r\\n"
#define RE_SPACE "\\s*"
#define RE_DOMAIN "<.+>"
#define RE_EMAIL "<(.+@.+)>"

/* COMMANDS: */

#define RE_CMND_NOOP "^NOOP" RE_CRLF
#define RE_CMND_HELO "^HELO:" RE_SPACE RE_DOMAIN RE_CRLF
#define RE_CMND_EHLO "^EHLO:" RE_SPACE RE_DOMAIN RE_CRLF
#define RE_CMND_MAIL "^MAIL FROM:" RE_SPACE RE_DOMAIN RE_CRLF
#define RE_CMND_RCPT "^RCPT TO:" RE_SPACE RE_EMAIL RE_CRLF
#define RE_CMND_VRFY "^VRFY:" RE_SPACE RE_DOMAIN RE_CRLF
#define RE_CMND_DATA "^DATA" RE_CRLF
#define RE_CMND_RSET "^RSET" RE_CRLF
#define RE_CMND_QUIT "^QUIT" RE_CRLF

/* MAIL CONTENT: */

#define RE_MAIL_END "^\\." RE_CRLF
#define RE_MAIL_DATA "[\\x00-\\x7F]+" RE_CRLF

/* RESPONSES: */

#define RE_RESP_READY "220 Ready\r\n"
#define RE_RESP_CLOSE "221 Close\r\n"
#define RE_RESP_OK "250 OK\r\n"
#define RE_RESP_START_MAIL "354 Waiting for data\r\n"

#define RE_RESP_ERR_WRONG_CMND "500 Syntax error, incorrect command\r\n"
#define RE_RESP_ERR_NOT_IMPL_CMND "502 Command not implemeted\r\n"
#define RE_RESP_ERR_BAD_SEQ "503 Bad sequence of commands\r\n"
#define RE_RESP_ERR_MAILBOX_UNAVAIL "550 Mailbox unavailable\r\n"
#define RE_RESP_ERR_MAILBOX_INCORRECT "553 Syntax error, incorrect email address\r\n"

#endif //SMTP_MTA_REXPRS_H
