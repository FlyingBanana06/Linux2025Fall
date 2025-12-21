HW13 - ROS Based Autonomous Driving Systems 

### 1. 主題

本次實驗的主題是 **ROS 2 基礎操作**，重點在於使用 `turtlesim` 模擬器以及 `rosbag` 資料錄製工具 。

### 2. 實驗過程

* 
**啟動模擬器**：安裝並運行 `turtlesim_node` 以及 `turtle_teleop_key` 鍵盤控制節點 。


* 
**錄製數據**：利用 `ros2 bag record -a` 指令錄製所有 Topic 的通訊數據（包含海龜的位置與控制指令） 。


* 
**分析資訊**：使用 `ros2 bag info` 指令檢視錄製檔案的時長、訊息數量及存儲格式 。


* 
**回放測試**：執行 `ros2 bag play` 將錄好的路徑重新在模擬器中播放出來 。



### 3. 學習成果

* 掌握了 ROS 2 基本節點（Nodes）與話題（Topics）的運作邏輯 。


* 學會如何備份與重現機器人的運行數據，這在自動駕駛開發中對於錯誤偵錯（Debugging）非常重要 。


---


### 1. Topic

The theme of this lab is **Basic ROS 2 Operations**, focusing on the `turtlesim` simulator and the `rosbag` data recording tool.

### 2. What I Did

* 
**Simulator Setup**: Installed and launched the `turtlesim_node` and the `turtle_teleop_key` node for manual control.


* 
**Data Recording**: Used `ros2 bag record -a` to capture all topic data, including turtle poses and velocity commands.


* 
**Bag Analysis**: Analyzed the recorded file using `ros2 bag info` to check duration, message counts, and topic details.


* 
**Data Playback**: Executed `ros2 bag play` to reproduce the recorded movement path within the simulator.



### 3. What I Learned

* Understood the fundamental logic of ROS 2 Nodes and Topics communication.


* Learned how to archive and replay robot mission data, which is a critical skill for debugging in autonomous driving system development.
