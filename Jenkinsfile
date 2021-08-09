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
        archiveArtifacts 'x64\\Release\\AgileSD_Payroll.exe'
        recordIssues()
      }
    }

    stage('test') {
      parallel {
        stage('test') {
          steps {
            bat 'x64\\Release\\AgileSD_Payroll.exe -ojunit'
            junit 'cpputest_PayrollTest.xml'
          }
        }

        stage('codeinspection') {
          steps {
            bat 'jb inspectcode AgileSD_Payroll.sln -o=inspectcode'
            archiveArtifacts 'inspectcode.xml'
          }
        }

      }
    }

  }
}