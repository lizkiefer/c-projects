Order 1:
0.0 A 4 # Mutex locked, A enters monitor
0.0 A 6 [count -> 1]
0.0 A 7 # Count is 1, going to line 7.1
0.0 A 7.1 [waiting -> A] # A leaves monitor
1.0 B 4 # Mutex locked, B enters monitor
1.0 C 4 # Mutex locked, C waits
1.0 B 6 [count -> 2]
1.0 B 7 # Count is 2, going to line 7.1
1.0 B 7.1 [waiting -> A, B] # B leaves monitor
# C enters monitor
1.1 C 6 [count -> 3]
1.1 C 7 # Count is 3, going to line 7.2
1.1 C 7.2 # Signal is given to release one of the waiting threads
1.1 C 8 [count -> 0]
1.1 C 9 # C leaves monitor
# May wake either A or B
1.2 A 8 [count -> 0] # A enters monitor
1.2 A 9 # A leaves monitor
# Signal is never called again, so B stays waiting


Order 2:
0.0 A 4 # Mutex locked, A enters monitor
0.0 A 6 [count -> 1]
0.0 A 7 # Count is 1, going to line 7.1
0.0 A 7.1 [waiting -> A] # A leaves monitor
1.0 B 4 # Mutex locked, B enters monitor
1.0 C 4 # Mutex locked, C waits
1.0 B 6 [count -> 2]
1.0 B 7 # Count is 2, going to line 7.1
1.0 B 7.1 [waiting -> A, B] # B leaves monitor
# C enters monitor
1.1 C 6 [count -> 3]
1.1 C 7 # Count is 3, going to line 7.2
1.1 C 7.2 # Signal is given to release one of the waiting threads
1.1 C 8 [count -> 0]
1.1 C 9 # C leaves monitor
# May wake either A or B
1.2 B 8 [count -> 0] # B enters monitor
1.2 B 9 # B leaves monitor
# Signal is never called again, so A stays waiting

