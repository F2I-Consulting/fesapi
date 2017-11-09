rm ../python/src/fesapi.py
rm ../python/src/fesapi.pyc
rm ../python/src/_fesapi.so
/home/philippe/appli/swig-3.0.5/bin/swig -c++ -python -o swigGeneratedPythonWrapper.cpp -outdir ../python/src/ swigModule.i
rm -rf build
python setup.py build_ext --build-lib ../python/src