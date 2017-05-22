echo "Building..."
g++ main.cpp -I$UNITY_ROOT/External/MonoBleedingEdge/builds/include/mono \
-I$UNITY_ROOT/Runtime/Mono \
-L$UNITY_ROOT/External/MonoBleedingEdge/ \
-DENABLE_MONO -DPLATFORM_STANDALONE -std=c++11
echo "Done."