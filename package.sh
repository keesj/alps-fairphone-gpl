#!/bin/sh
DATE=$(date +"%Y-%d-%m")
git archive master --prefix=alps-fairphone-gpl-$DATE/ | bzip2 > alps-fairphone-gpl-$DATE.tar.bz2
