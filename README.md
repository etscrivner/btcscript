# btcscript

Command-line Bitcoin Script diassembler.

## Usage

Give a file with Script bytecode as a single line hex string `test.hex`:

```
4730440220210d105c07282560683fc11591a22ca1494664d427643dede7d4a58101047569022077c8cdb8f0964a35cdcecc3149169d9e9fb2313c9aca026e17f60b43f0f4ef82012103921d49f08ee95b41454543e7356bd8631cf80b00c3a2b9c156cacf97524827d6eric
```

We can print the disassembly by running:

```
btcscript test.hex
```

The output should be:

```
OP_PUSHBYTES_71 30440220210d105c07282560683fc11591a22ca1494664d427643dede7d4a58101047569022077c8cdb8f0964a35cdcecc3149169d9e9fb2313c9aca026e17f60b43f0f4ef8201 OP_PUSHBYTES_33 03921d49f08ee95b41454543e7356bd8631cf80b00c3a2b9c156cacf97524827d6
```

## Compiling

```
make
```

## Testing

```
make check
```
