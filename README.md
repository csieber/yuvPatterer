# yuvPatterer

Generate quality oscillation patterns out of raw yuv video files.

## Requirements

 - premake4
 - g++
 - libboost-system-dev 

The YUV files have to be all the same size and color format.
 
## Compile

Use premake4 to create the make files:

```bash
git clone git@github.com:csieber/yuvPatterer.git
cd yuvPatterer/
premake4 gmake
```

Build the application:

```bash
cd build/
make
```

## Usage

```
Usage: svcPatter [OPTION] [YUV-Base]

Options:
  --help                Help
  -i [ --yuv-base ] arg Input YUV base filename
  -w [ --width ] arg    Input YUV width
  -h [ --height ] arg   Input YUV height
  -p [ --pattern ] arg  Pattern file
```

Check the vagrant [here](vagrant/README.md) for an example how to use the yuvPatterer.

## Citing

Please cite the following publication if you use this application:

```
@inproceedings{sieber2013implementation,
  title={Implementation and User-centric Comparison of a Novel Adaptation Logic for DASH with SVC},
  author={Sieber, Christian and Ho{\ss}feld, Tobias and Zinner, Thomas and Tran-Gia, Phuoc and Timmerer, Christian},
  booktitle={2013 IFIP/IEEE International Symposium on Integrated Network Management (IM 2013)},
  pages={1318--1323},
  year={2013},
  organization={IEEE}
}
```

