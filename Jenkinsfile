pipeline {
  agent any
  stages {
    stage('clone') {
      steps {
        git(url: 'https://github.com/h1day/AgileSD_Payroll', branch: 'main', changelog: true)
      }
    }

    stage('build') {
      steps {
        bat 'msbuild AgileSD_Payroll.sln /p:configuration=release /p:platform=x64'
      }
    }

    stage('test') {
      steps {
        bat 'x64\\Release\\AgileSD_Payroll.exe -ojunit'
      }
    }

    stage('archive') {
      parallel {
        stage('archive') {
          steps {
            junit 'cpputest_PayrollTest.xml'
          }
        }

        stage('') {
          steps {
            archiveArtifacts 'x64\\Release\\AgileSD_Payroll.exe'
          }
        }

      }
    }

  }
}