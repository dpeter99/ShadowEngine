echo Setting up docs repo docs
cd ..
cd %FOLDER_TO_PUSH%
echo %cd%
dir

git config --global user.email "dpeter99@gmail.com"
git config --global user.name "Doc gen"

git init
git remote add origin "https://x-access-token:%GITHUB_TOKEN%@github.com/%GITHUB_REPOSITORY%"
git pull HEAD:%PUSH_TO_BRANCH%

dir