# php-fpm的监控页

## php-fpm的设置
*   修改php-fpm的设置文件，具体文件视每个人的安装方法而异，
    增加一行，

        pm.status_path = /status

*   重启php-fpm，具体操作视每个人的安装方法而异。

## nginx的设置
*    修改nginx.conf,增加一块，

        location /status {
            include fastcgi_params;
            fastcgi_pass 127.0.0.1:9000;
            fastcgi_param SCRIPT_FILENAME $fastcgi_script_name;
        }

*   重启nginx

## 验证
浏览器打开 http://127.0.0.1/status 。
