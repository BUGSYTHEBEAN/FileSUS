# FileSUS
File System Universal test Suite

A tool to benchmark file systems that runs natively on Windows and Linux. We benchmarked Windows 11’s implementation of NTFS and Linux’s ext4 on the same machine to reveal the relative performance and best use cases for each file system. We find that ext4 has universally lower latency by an order of magnitude, two to five times faster write throughput and faster read throughput at payload sizes lower than 4KB.

# Results
##Throughput (MB/s)
![image](https://user-images.githubusercontent.com/16845012/145524013-cfe0005f-5bea-4bf8-ab6a-9fc361850481.png)
##Throughput at Different Payload Sizes
![image](https://user-images.githubusercontent.com/16845012/145524046-d76ea2a9-5b69-487c-ab7d-495df70f882d.png)
![image](https://user-images.githubusercontent.com/16845012/145524063-6175774a-1b4a-412e-b824-ccb6a86213a8.png)
##Latency (nanoseconds)
![image](https://user-images.githubusercontent.com/16845012/145524090-d6160844-ccf6-4324-8e64-d5ea92dd0cc8.png)
![image](https://user-images.githubusercontent.com/16845012/145524129-c1ce4740-dc07-4afb-bd7c-f5c99f5d385e.png)
