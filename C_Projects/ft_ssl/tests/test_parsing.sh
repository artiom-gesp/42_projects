#/bin/sh

make -C ..

out="$(../ft_ssl md5)"
echo $out

if [ "$out" -eq $(openssl) ]; then
  echo "Ok"
else
  echo "Ko"
fi