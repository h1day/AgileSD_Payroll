pipeline {
  agent any
  stages {
    stage('clone') {
      steps {
        git(url: 'https://github.com/h1day/AgileSD_Payroll', branch: 'main', changelog: true)
      }
    }

    stage('') {
      steps {
        bat 'msbuild AgileSD_Payroll.sln /p:configuration=release /p:platform=x64'
      }
    }

  }
}