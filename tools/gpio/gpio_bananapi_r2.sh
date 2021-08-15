#!/bin/bash
# http://forum.banana-pi.org/t/how-to-use-banana-pi-bpi-r2s-gpio-s/4480

DIR=/sys/class/gpio/

global_gpio_offset=0

mt_gpio_init()
{
  pin=$1

  EXPORT=/sys/class/gpio/export
  UNEXPORT=/sys/class/gpio/unexport


  name=`ls $DIR | grep chip`
  if [ x${name} != x ]; then
    echo "chip id : $name"
  else
    echo "No available gpio chip"
    exit 1
  fi

  base=`cat ${DIR}/${name}/base`
  echo "base=$base"

  gpio_offset=`echo $((base+$pin))`
  global_gpio_offset=$gpio_offset
  echo "offset=$gpio_offset"

  if [ -d ${DIR}/gpio${gpio_offset} ]; then
    echo "${DIR}/gpio${gpio_offset} is dir"
    return 0
  else
    echo "RUN: echo ${gpio_offset} > ${EXPORT}"
    echo ${gpio_offset} > ${EXPORT}
  fi
}

mt_gpio_init $1

if [ $2 == 'dir' ]; then
  echo "dir: ${DIR}/gpio${global_gpio_offset}/direction"
  if [ $3 == 'out' ]; then
    echo out > ${DIR}/gpio${global_gpio_offset}/direction
  else
    echo in > ${DIR}/gpio${global_gpio_offset}/direction
fi
elif [ $2 == 'val' ]; then
  echo "val_dir: ${DIR}/gpio${global_gpio_offset}/value"
  if [ $# == 2 ]; then
    cat ${DIR}/gpio${global_gpio_offset}/value
  elif [ $# == 3 ]; then
    echo $3 >  ${DIR}/gpio${global_gpio_offset}/value
  fi   
fi 
