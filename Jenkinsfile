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
      parallel {
        stage('test') {
          steps {
            bat 'x64\\Release\\AgileSD_Payroll.exe -ojunit'
          }
        }

        stage('inspectcode') {
          steps {
            bat 'jb inspectcode AgileSD_Payroll.sln -o inspectcode.xlm'
          }
        }

      }
    }

    stage('archive') {
      parallel {
        stage('archive') {
          steps {
            junit 'cpputest_PayrollTest.xml'
          }
        }

        stage('SaveArtifact') {
          steps {
            archiveArtifacts 'x64\\Release\\AgileSD_Payroll.exe'
          }
        }

      }
    }

  }
}