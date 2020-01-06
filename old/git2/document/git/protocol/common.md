# DOCUMENTATION COMMON TO PACK AND HTTP PROTOCOLS

## ABNF NOTATION

_ABNF notation_ as described by [RFC 5234](https://tools.ietf.org/html/rfc5234) is used within the protocol documents,
expect the following replacement core rules are used:

```
  HEXDIGIT  =  DIGIT / "a" / "b" / "c" / "d" / "e" / "f"
```

## WE ALSO DEFINE THE FOLLOWING COMMON RULES:

```
  NUL       =  %x00
  zero-id   =  40*"0"
  obj-id    =  40*(HEXDIGIT)
  
  refname   =  "HEAD"
  refname/  =  "refs/"  # see discussion below
```

A _refname_ is a hierarchical octet string beginning with "_refs/_" and not violating the '_git-check-ref-format_' command's validation rules.
More specifically, they:

 - They can include slash '/' for hierarchical (directory) grouping, but no slash-separated component can begin with a dot '.'.
 - They must contain at least one '/'. This enforces the presence of a category like '_heads/_', '_tags/_' etc, but the actual names are not restricted.
 - They cannot have two consecutive dots '..' anywhere.
 - They cannot have ASCII control characters (i.e. bytes whose values are lower than \040, or \177 'DEL'), space, tilde '~', caret '^', colon ':', question-mark '?', asterisk '*', or open bracket '[' anywhere.
 - They cannot end with a slash '/' or a dot '.'.
 - They cannot end with the sequence '.lock'.
 - They cannot contain a sequence '@{'.
 - They cannot contain a '\\'.

## PKT-LINE FORMAT

Much (but not all) of the payload is described around _pkt-lines_.

A _pkt-line_ is a variable length binary string. The first four bytes of the line, the pkt-len, indicates the total length of the line, in hexadecimal.
The _pkt-len_ includes the 4 bytes used to contain the length's hexadecimal representation.

A _pkt-line_ MAY contain binary data, so implementors MUST ensure _pkt-line_ parsing/formatting routines are 8-bit clean.

A non-binary line SHOULD BE terminated by an LF, which if present MUST be included in the total length. Receivers MUST treat _pkt-lines_ with non-binary data the same whether or not they contain the trailing LF (stripping the LF if present, and not complaining when it is missing).

The maximum length of a _pkt-line_'s data component is 65516 bytes.
Implementations MUST NOT send _pkt-line whose length exceeds 65520 (65516 bytes of payload + 4 bytes of length data).

Implementations SHOULD NOT send an empty _pkt-line_ ("0004").

A _pkt-line_ with a length field of 0 ("0000"), called a flush-pkt, is a special case and MUST be handled differently than an empty _pkt-line_ ("0004").

```
  pkt-line     =  data-pkt / flush-pkt
  
  data-pkt     =  pkt-len pkt-payload
  pkt-len      = 4*(HEXDIGIT)
  pkt-payload  = (pkt-len - 4)*(OCTET)
  
  flush-pkt    = "0000"
```

Examples (as C-style strings):

| PACKET LINE    | ACTUAL VALUE |
| -------------- | ------------ |
| "0006a\n"      | "a\n"        |
| "0005a"        | "a"          |
| "000bfoobar\n" | "foobar\n"   |
| "0004"         | ""           |

## SEE

 - [DOCUMENTATION COMMON TO PACK AND HTTP PROTOCOLS](https://github.com/git/git/blob/master/Documentation/technical/protocol-common.txt)