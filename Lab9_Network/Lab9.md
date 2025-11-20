# **Lab9 Networking — 簡短心得**

## **主題說明**

本次 Lab 主題是 **Linux 網路設定（Networking）**，重點在於學習如何查看網路介面資訊，以及透過 **GUI 與 netplan** 兩種方式設定 **靜態 IP（Static IP）**，並且練習如何恢復設定。

---

## **做了什麼**

1. 使用 `ip addr` 查看原本的網路介面資訊。
2. 透過 **GUI** 將 IPv4 改為手動模式並輸入指定的靜態 IP。
3. 檢查 GUI 設定後的結果。
4. 進入 `/etc/netplan/` 找到設定檔，備份 `.yaml`。
5. 編輯 netplan 設定檔，將 IP 改為老師要求的靜態 IP。
6. 使用 `sudo netplan try` 與 `sudo netplan apply` 驗證並套用設定。
7. 測試成功後，再使用還原指令將設定復原。

---

## **遇到的困難**

* `netplan try` 出現了 **Permissions too open** 的警告，需要手動調整檔案權限。
* 依照課堂範例套用後，`gateway4` 產生 deprecated 警告。

---

## **學到的事情**

* 了解 **Linux 如何管理網路設定**，尤其是 netplan 的配置方式。
* 學到如何透過 `ip addr` 與 GUI 驗證網路狀態。
* 學到備份、修改、恢復 netplan 的完整流程。
* 了解常見警告訊息與其原因，以及如何修正。

---

# **Lab9 Networking — Short Reflection**

## **Topic Overview**

This lab focuses on **Linux networking configuration**, mainly on how to inspect network interfaces and how to set a **static IP** using both **GUI** and **netplan**. It also includes restoring the system back to its original state.

---

## **What I Did**

1. Checked the original network interface using `ip addr`.
2. Set the IPv4 manually through the **GUI** using the IP provided by the instructor.
3. Verified the changes using `ip addr`.
4. Found the netplan configuration file under `/etc/netplan` and created a backup.
5. Edited the YAML file to configure a static IP.
6. Applied the configuration using `sudo netplan try` and `sudo netplan apply`.
7. Restored the original YAML file after testing.

---

## **Difficulties Encountered**

* Received **Permissions too open** warnings in netplan, requiring manual permission fixes.
* The `gateway4` directive shows a deprecated warning even though the lab requires using it.

---

## **What I Learned**

* How Linux manages networking through netplan.
* How to validate settings using both GUI and command line tools.
* The importance of backing up configuration files.
* How to interpret common netplan warnings and handle them correctly.
