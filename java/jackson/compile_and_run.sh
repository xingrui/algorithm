annotations=~/.m2/repository/com/fasterxml/jackson/core/jackson-annotations/2.8.5/jackson-annotations-2.8.5.jar
core=~/.m2/repository/com/fasterxml/jackson/core/jackson-core/2.8.5/jackson-core-2.8.5.jar
databind=~/.m2/repository/com/fasterxml/jackson/core/jackson-databind/2.8.5/jackson-databind-2.8.5.jar
lombok=~/.m2/repository/org/projectlombok/lombok/1.16.8/lombok-1.16.8.jar
springframework=~/.m2/repository/org/springframework/spring-web/4.3.5.RELEASE/spring-web-4.3.5.RELEASE.jar
beans=~/.m2/repository/org/springframework/spring-beans/4.3.5.RELEASE/spring-beans-4.3.5.RELEASE.jar
springcore=~/.m2/repository/org/springframework/spring-core/4.3.5.RELEASE/spring-core-4.3.5.RELEASE.jar
export CLASSPATH=.:$databind:$annotations:$core:$lombok:$springframework:$beans:$springcore
javac JacksonTester.java && java JacksonTester
