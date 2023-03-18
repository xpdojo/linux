"""
python3 page_reclaim.py
"""
import numpy

# htop으로 확인해보면 Memory가 가득 찬 후 Swap이 증가하는 것을 확인할 수 있다.
# 만약 Swap 영역이 가득 차면, 프로세스가 종료된다.
result = [numpy.random.bytes(1024*1024*32) for x in range(1024)]
print(len(result))
