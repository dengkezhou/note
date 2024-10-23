git使用说明

### 问题

1 **分支领先于 origin/dev_pull_requests n个提交**

目标：使当前分支与远程分支保持一致，丢弃之前所有修改。

现象：在与远程分支同步后，使用git pull 发现当前分支领先于远程分支，git status出现下面提示。

```
you branch is ahead of "origin/dev_pull_requests" by 1 commit
	use git push to publish you local commits
```

原因：在同步之前已经做过commit操作但没有上传，在同步之后仍然保留了这些修改。

解决：

```shell
# 退回分支到origin/dev_pull_requests，此时本地代码为origin/dev_pull_requests代码 + 本地修改
git reset origin/dev_pull_requests

# 退回修改，此时代码为origin/dev_pull_requests + 新增文件
git restore ./

#删除 git  status 中为跟随的文件
rm  .....
```

**2 git pull 时保存本地修改**

```
git stash
git pull
git stash pop stash{0}

/*若有冲突需要解决冲突，然后使用*/

/*查看保存的信息*/
git stash list
```

