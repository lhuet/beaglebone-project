echo "--- test JRE Zero VM"
java -version
#java -server -ms128m -mx128m -jar dacapo-9.12-bach.jar avrora
java -server -ms128m -mx128m -jar dacapo-9.12-bach.jar fop
java -server -ms128m -mx128m -jar dacapo-9.12-bach.jar jython
java -server -ms128m -mx128m -jar dacapo-9.12-bach.jar pmd
java -server -ms128m -mx128m -jar dacapo-9.12-bach.jar xalan


echo "--- test JRE JamVM ---"
java -jamvm -version
java -jamvm -server -ms128m -mx128m -jar dacapo-9.12-bach.jar avrora
java -jamvm -server -ms128m -mx128m -jar dacapo-9.12-bach.jar fop
java -jamvm -server -ms128m -mx128m -jar dacapo-9.12-bach.jar jython
java -jamvm -server -ms128m -mx128m -jar dacapo-9.12-bach.jar pmd
java -jamvm -server -ms128m -mx128m -jar dacapo-9.12-bach.jar xalan

