# FileSUS
**File S**ystem **U**niversal Test **S**uite

Created at UW-Madison for CS 736—Advanced Operating Systems—by [Andrei Freund](https://github.com/BUGSYTHEBEAN) and [Natan Lidukhover](https://github.com/natanlidukhover)

A tool to benchmark file systems that runs natively on Windows and Linux. We benchmarked Windows 11’s implementation of NTFS, Linux’s ext4, Linux's XFS, and NTFS mounted on Linux (read-only) on the same machine to reveal the relative performance and best use cases for each file system. We find that ext4 and XFS have universally lower latency by an order of magnitude, two to five times faster write throughput and faster read throughput at payload sizes lower than 4KB.

# Results
## Throughput (MB/s)
![image](https://user-images.githubusercontent.com/16845012/146504379-7bfb5a67-e3ec-435b-9233-3d980f570e0b.png)
## Throughput at Different Payload Sizes
![image](https://user-images.githubusercontent.com/16845012/146504416-1059ce29-91e1-4339-98b4-658a4c947cb8.png)
![image](https://user-images.githubusercontent.com/16845012/146504450-7c0147e4-5621-4f07-9031-421c8fb29521.png)
## Latency (nanoseconds)
![image](https://user-images.githubusercontent.com/16845012/146504545-f0f6978d-c89e-4562-9755-b897dd614291.png)
![image](https://user-images.githubusercontent.com/16845012/146504582-3f76a551-76e7-4ab9-9f67-5a631c72d67e.png)

