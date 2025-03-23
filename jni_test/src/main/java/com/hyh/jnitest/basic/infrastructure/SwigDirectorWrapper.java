package com.hyh.jnitest.basic.infrastructure;

/**
 * TODO
 *
 * @author eriche 2025/3/23
 */
public class SwigDirectorWrapper {
    private transient long swigCPtr;
    protected transient boolean swigCMemOwn;

    public SwigDirectorWrapper(long cPtr, boolean cMemoryOwn) {
        swigCMemOwn = cMemoryOwn;
        swigCPtr = cPtr;
    }

    public static long getCPtr(SwigDirectorWrapper obj) {
        return (obj == null) ? 0 : obj.swigCPtr;
    }

    public static long swigRelease(SwigDirectorWrapper obj) {
        long ptr = 0;
        if (obj != null) {
            if (!obj.swigCMemOwn)
                throw new RuntimeException("Cannot release ownership as memory is not owned");
            ptr = obj.swigCPtr;
            obj.swigCMemOwn = false;
            obj.delete();
        }
        return ptr;
    }

    protected void finalize() {
        delete();
    }

    public synchronized void delete() {
        if (swigCPtr != 0) {
            if (swigCMemOwn) {
                swigCMemOwn = false;
                _DeleteSwigDirectorWrapper(swigCPtr);
            }
            swigCPtr = 0;
        }
    }

    @SuppressWarnings("all")
    public <T> T acquire(IDirectorConstructor<T> constructor) {
        if (IsJObject()) {
            return (T) GetJObject();
        } else {
            long cPtr = GetCPtr();
            return (cPtr == 0) ? null : constructor.create(cPtr);
        }
    }

    public SwigDirectorWrapper(SwigDirectorWrapper other) {
        this(_NewSwigDirectorWrapper(SwigDirectorWrapper.swigRelease(other), other), true);
    }

    private boolean IsJObject() {
        return _IsJObject(swigCPtr, this);
    }

    private boolean IsCPtr() {
        return _IsCPtr(swigCPtr, this);
    }

    private Object GetJObject() {
        return _GetJObject(swigCPtr, this);
    }

    private long GetCPtr() {
        return _GetCPtr(swigCPtr, this);
    }


    private static native long _NewSwigDirectorWrapper(long cPtr, SwigDirectorWrapper wrapper);

    private static native void _DeleteSwigDirectorWrapper(long cPtr);

    private static native boolean _IsJObject(long cPtr, SwigDirectorWrapper wrapper);

    private static native boolean _IsCPtr(long cPtr, SwigDirectorWrapper wrapper);

    private static native Object _GetJObject(long cPtr, SwigDirectorWrapper wrapper);

    private static native long _GetCPtr(long cPtr, SwigDirectorWrapper wrapper);

    public interface IDirectorConstructor<T> {
        T create(long cPtr);
    }

}
