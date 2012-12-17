export PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/local/games:/usr/games:/home/pi/jdk_arm/ejre1.7.0_06/bin
echo "--- TEST EJRE ---"
java -version
java -ms128m -mx128m -jar dacapo-9.12-bach.jar avrora
java -ms128m -mx128m -jar dacapo-9.12-bach.jar eclipse 
java -ms128m -mx128m -jar dacapo-9.12-bach.jar fop
java -ms128m -mx128m -jar dacapo-9.12-bach.jar jython
java -ms128m -mx128m -jar dacapo-9.12-bach.jar luindex
java -ms128m -mx128m -jar dacapo-9.12-bach.jar lusearch        
java -ms128m -mx128m -jar dacapo-9.12-bach.jar pmd
java -ms128m -mx128m -jar dacapo-9.12-bach.jar xalan


export PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/local/games:/usr/games:/home/pi/jdk_arm/jdk1.7.0_06/bin
echo "--- TEST JDK ---"
java -ms128m -mx128m -jar dacapo-9.12-bach.jar avrora
java -ms128m -mx128m -jar dacapo-9.12-bach.jar eclipse        
java -ms128m -mx128m -jar dacapo-9.12-bach.jar fop
java -ms128m -mx128m -jar dacapo-9.12-bach.jar jython
java -ms128m -mx128m -jar dacapo-9.12-bach.jar luindex
java -ms128m -mx128m -jar dacapo-9.12-bach.jar lusearch       
java -ms128m -mx128m -jar dacapo-9.12-bach.jar pmd
java -ms128m -mx128m -jar dacapo-9.12-bach.jar xalan





