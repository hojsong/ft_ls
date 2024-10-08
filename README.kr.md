ft_ls
이 프로젝트는 C 언어를 사용하여 ls 명령어와 그 옵션 -a, -l, -r, -R, -t를 구현합니다. 파일 시스템의 내용을 나열하는 기능을 제공합니다.
프로젝트 개요
목적: C로 ls 명령어와 그 옵션 -a, -l, -r, -R, -t를 구현하여 파일 시스템 내용을 나열하는 기능을 제공합니다.
기능:

기본 ls: 디렉토리의 내용을 나열합니다.
옵션 -a: 숨김 파일을 포함하여 나열합니다.
옵션 -l: 권한, 링크 수, 소유자, 그룹, 크기, 최종 수정 날짜 등 파일 세부 정보를 나열합니다.
옵션 -r: 파일을 역순으로 나열합니다.
옵션 -R: 발견된 하위 디렉토리를 재귀적으로 나열합니다.
옵션 -t: 수정 시간순으로 파일을 정렬하여 나열합니다.

사용된 함수

파일 및 디렉토리 처리: opendir, readdir, closedir, stat, lstat, readlink
사용자 및 그룹 정보: getpwuid, getgrgid
시간 관련: time, ctime
메모리 관리: malloc, free
오류 처리: perror, strerror
프로그램 종료: exit

이 프로젝트는 파일 시스템 내용을 나열하고 관리하는 데 필요한 기본 기능을 복제하는 것을 목표로 합니다. 코드 구조와 사용된 함수에 대한 자세한 설명은 프로젝트 소스 코드 내의 주석을 참조하세요.
프로젝트에 대한 피드백이나 질문이 있으시면 이슈를 열어 주세요. 🌟
이 가이드는 프로젝트 구현에 사용된 함수와 옵션에 대한 정보를 바탕으로 작성되었습니다. 정확성을 보장하기 위해 모든 노력을 기울였지만, 오류가 있을 수 있음을 알려드립니다.