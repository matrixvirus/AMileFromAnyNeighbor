# 7 layers model for network

## 1 which 7 layers
from up to down
*   application
*   presentation
*   session
*   transport
*   network
*   data link
*   pyhsical

## 2 what data type each layer transfer

| layer       |  data     |
| ---------   | --------- |
| transport   | datagram  |
| network     | packet    |
| data link   | frame     |
| physical    | bit       |

note,the 'frame' and 'packet' are fundamentaly the same thing.

## 3 what is the difference between bridges switches and routers
1. bridges work on link level,transfer frames
2. switches work on network level,transfer packet
3. routers work on transport level,transter datagram

for the details of difference between bridge,switch,router,can see book

    computer network a system approach,
    chapter 3.2
