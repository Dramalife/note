|No|Options|Details|Others|
|--|--|--|--|
| |z|\--gzip, --gunzip --ungzip| |
| |c|\--create,create a new archive| |
| |x|\--extract, --get, extract files from an archive| |
| |v|\--verbose, verbosely(ÏêÏ¸µØ) list files processed| |
| |f|\--file ARCHIVE, use archive file or device ARCHIVE| |
| |k|\--keep-old-files, don't replace existing files when extracting, treat them as errors| |
| | | | |
| | | | |
| |C|--directory DIR, change to directory DIR| |
| | | | |
| | | | |


##Samples

### Compression
```bash
tar zcvf NAME.tgz /SourcePath
```

### Decompression
```bash
#"-C" set destination path
#"-k" keep old(existed) file
tar zxvf NAME.tgz -C /DestinationPath
```
