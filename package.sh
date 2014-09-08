#!/bin/sh
DATE=$(date +"%Y-%m-%d")
git archive master --prefix=alps-fairphone-gpl-kernel-$DATE/ | bzip2 > alps-fairphone-gpl-kernel-$DATE.tar.bz2
