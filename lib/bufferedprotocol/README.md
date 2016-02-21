## Protocol Packet Format

### Motivation

When sending multiple pieces of data (e.g. multiple JSON documents, or multiple images), TCP doesn't provide any mechanism to distinguish between the previous and the next byte. In other words, two JSON documents being sent out via TCP will be a part of the same "stream". Hence, there's no way to know whether or not byte (say, number 244) belongs to the last document, or to the next document.

We are thus responsible for designing a protocol that ensures that two documents are well distinguished.

### The Protocol

There will be a concept of a "payload". A payload will begin with a 24-bit big-endian integer, which will represent the *size* of the payload in bytes. We will call that size `n`. We will then buffer `n` bytes, until signalling that we have received the intended payload.

### Sending

```cpp
unsigned char header[] = {
  static_cast<unsigned char>(size & 0xff)
  static_cast<unsigned char>((size >> 8) & 0xff),
  static_cast<unsigned char>((size >> 16) & 0xff),
}
```

### Receiving

```cpp
int size =
  (
    header[0] |
    (header[1] << 8) |
    (header[2] << 16)
  ) &
  0x00FFFFFF;
```
