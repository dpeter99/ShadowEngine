echo Building Documentation
echo %cd%
cd ..
echo %cd%
dir
echo %FOLDER_TO_PUSH%
cd %FOLDER_TO_PUSH%
dir
echo %cd%

git init
git remote add origin "https://x-access-token:$GITHUB_TOKEN@github.com/$GITHUB_REPOSITORY"
git add .
git commit -m "ApiGen Code Docs Regenerated"
git push origin "master:${PUSH_TO_BRANCH}" -f