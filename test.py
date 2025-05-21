import sys
sys.path.append(r"C:\Users\kb150\Documents\ProjekcikTP3\build\Debug")

import projekcikTP3_python

projekcikTP3_python.DFT([1, 2, 5, 9, 2, 3])
data = [complex(1, 0), complex(6, 3), complex(9, 2), complex(-8, 2), complex(22, 3), complex(0, 0)]
projekcikTP3_python.I_DFT(data)
image = [
    [1, 2, 3, 2, 1, 10, 11, 12, 11, 10],
    [4, 5, 6, 5, 4, 13, 14, 15, 14, 13],
    [7, 8, 9, 8, 7, 16, 17, 18, 17, 16],
    [4, 5, 6, 5, 4, 13, 14, 15, 14, 13],
    [1, 2, 3, 2, 1, 10, 11, 12, 11, 10],
]
projekcikTP3_python.TestFilter2D(image)
projekcikTP3_python.DFTFiltre_Reversed([1, 2, 5, 9, 2, 3])
projekcikTP3_python.Filter1D([-10,10,-11,11,-12,12,5,6], 3)
projekcikTP3_python.sinus(1.0, 0.0, 2.0, 100)
projekcikTP3_python.cosinus(2.0, 0.0, 1.0, 200)
projekcikTP3_python.rectangular(5.0, 0.0, 1.0, 500)
projekcikTP3_python.sawtooth(3.0, 0.0, 1.0, 300)
