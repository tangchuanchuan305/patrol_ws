# ROS 2 常用命令
## 节点
    ros2 node list
    ros2 node info <节点名>

## Topic

    ros2 topic list
    ros2 topic info <话题名>
    ros2 topic echo <话题名> --once
    ros2 topic hz <话题名>

## 参数
    ros2 param list<节点名>
    ros2 param get <节点名> <参数名>
    ros2 param set <节点名> <参数名> <值>

尖括号表示需要替换的占位内容，不要原样输入终端。例如：
  ros2 param get /velocity_publisher angular_speed
