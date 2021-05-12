# U-disk tools

http://f.dataguru.cn/thread-267226-1-1.html

http://rufus.akeo.ie/




# Code view

###### Opengrok

https://github.com/OpenGrok/OpenGrok/wiki/How-to-install-OpenGrok

http://algopadawan.blogspot.co.uk/2012/07/installing-opengrok-on-windows.html

WEB-INF\web.xm
```
  <context-param>
  <param-name>CONFIGURATION</param-name>
  <param-value>G:\opengrok\configuration.xml</param-value>
  <description>Full path to the configuration file where OpenGrok can read it's configuration</description>
  </context-param>
  -------Added the below------
  <context-param>
  <param-name>SRC_ROOT</param-name>
  <param-value>Z:\opengrok</param-value>
  </context-param>
  <context-param>
  <param-name>DATA_ROOT</param-name>
  <param-value>G:\grokdata</param-value>
  </context-param>
```

Index the source
```
java -jar G:\opengrok\lib\opengrok.jar -W G:\opengrok\configuration.xml -c G:\ctags58\ctags.exe -P -s Z:\opengrok -d G:\opengrok\grokdata
```




# SCM

diffuse
