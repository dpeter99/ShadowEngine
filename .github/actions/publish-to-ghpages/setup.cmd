echo Setting up docs repo docs
cd ..
mkdir %FOLDER_TO_PUSH%
cd %FOLDER_TO_PUSH%
echo %cd%
dir

echo ####GIT COMMANDS ####

git config --global user.email "dpeter99@gmail.com"
git config --global user.name "Doc gen"

echo Git init
git init
echo git add remote
git remote add origin "https://x-access-token:%GITHUB_TOKEN%@github.com/%GITHUB_REPOSITORY%"
echo list remotes
git remote -v
echo pull
git pull origin %PUSH_TO_BRANCH%