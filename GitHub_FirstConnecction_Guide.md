# 第一次連接 GitHub 注意事項與完整流程

---

## 一、安裝與環境準備
### 1 安裝 Git
- 下載網址：[https://git-scm.com/download/win](https://git-scm.com/download/win)
- 安裝時務必勾選：**Add Git Bash to PATH**  
  （否則 PowerShell / VS Code 找不到 git 指令）

### 2 驗證安裝
重新開啟 PowerShell 或 VS Code 終端機：
```bash
git --version
```
應顯示類似：
```
git version 2.46.0.windows.1
```

---

## 二、建立專案連接 GitHub

### 1 進入專案資料夾
```powershell
cd "C:\Users\"username"\OneDrive\文件\PlatformIO\Projects\Avionics_STD" *注意這是你放專案的位置
```

### 2 初始化 Git
```bash
git init
```

### 3 新增全部檔案
```bash
git add .
```

### 4 設定作者資訊（第一次必做）
```bash
git config --global user.name "使用者名稱"
git config --global user.email "你的GitHub註冊Email"
```

### 5 提交初始版本
```bash
git commit -m "Initial commit"
```

---

## 三、連接 GitHub 儲存庫

### 1 在 GitHub 建立新 repo
- 名稱：`Avionics_STD`
- 不要勾選 README、LICENSE

### 2 綁定遠端
```bash
git remote add origin https://github.com/你的使用者名稱/Avionics_STD.git
```

### 3 設定主分支
```bash
git branch -M main
```

### 4 上傳
```bash
git push -u origin main
```

若出現登入視窗，輸入 GitHub 帳密或 Token（若開啟 2FA）。

---

## 四、常見錯誤與解法

| 錯誤訊息 | 原因 | 解法 |
|-----------|------|------|
| `git : Command not found` | 未安裝 Git 或未加入 PATH | 重新安裝 Git 並重啟 VS Code |
| `Author identity unknown` | 未設定姓名與 email | 執行 `git config --global user.name` 與 `user.email` |
| `error: src refspec main does not match any` | 尚未 commit | 先執行 `git commit -m "Initial commit"` |
| `remote: Repository not found` | GitHub repo 尚未建立或網址錯誤 | 確認 repo 已存在，網址無多餘 `/` |
| `Authentication failed` | 帳密錯誤或需使用 Token | 於 GitHub 建立 Personal Access Token (PAT) |

---

## 五、成功驗證標準
推送後顯示：
```
Enumerating objects...
Counting objects...
Writing objects...
To https://github.com/你的使用者名稱/Avionics_STD.git
 * [new branch] main -> main
branch 'main' set up to track 'origin/main'.
```
代表上傳成功。  
在瀏覽器開啟：  
👉 https://github.com/你的使用者名稱/Avionics_STD  

即可看到完整專案結構。

---

## 六、後續操作（更新時使用）
```bash
git add .
git commit -m "更新內容"
git push
```

---

## 七、建議加入 .gitignore
建立 `.gitignore`，內容如下：
```
.pio/
.vscode/
*.elf
*.bin
*.hex
*.map
.DS_Store
Thumbs.db
```
防止暫存或編譯檔被上傳。

---

## 八、邀請組員協作
1. 進入 GitHub 專案 → `Settings` → `Collaborators`
2. 按 **Add people**，輸入他們的 GitHub 帳號
3. 權限建議：`Write`
4. 組員接受邀請後執行：
   ```bash
   git clone https://github.com/你的使用者名稱/Avionics_STD.git
   ```

---

## 九、結論
 你的流程中發生的主要問題：
1. 未安裝 Git → `git : command not found`
2. 未加 `.` → `Nothing specified, nothing added`
3. 拼錯 commit → `commot`
4. 未設定身份 → `Author identity unknown`
5. 沒有 commit → `src refspec main does not match any`
6. 遠端不存在 → `Repository not found`
→ 全部問題已在此文件中整理完畢。

---

**作者：Renyilin0115**  
淡江大學航電組 · 2025.10.22  
