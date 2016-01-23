# Vagrant Example

## Requirements

 - Vagrant
 - VirtualBox
 
## Setup

Clone the repository, spin up the VM and ssh into the machine:

```bash
git clone git@github.com:csieber/yuvPatterer.git
cd yuvPatterer/vagrant/

vagrant up
vagrant shh
```

Two quality levels and a example pattern file are located in the vagrant/samples folder.

Call the yuvPatterer to create a file with oscilation quality:

```bash
cd /yuvPatterer/vagrant

../bin/yuvPatterer_d -i samples/ToS_lowSITI.yuv -w 640 -h 360 -p samples/pattern_example.txt
```

The output should look like this:

```
Start reading pattern file..
Finished reading pattern file..
Frame 48 quitting.
```

You can play the resulting YUV file using VLC:

```bash
vlc --demux rawvideo --rawvid-fps=24 --rawvid-width 640 --rawvid-height 360 --rawvid-chroma I420 samples/ToS_lowSITI.yuv.out.0000.yuv
```

