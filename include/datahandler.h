#ifndef _DATAHANDLER_H_
#define _DATAHANDLER_H_

#include <deque>

namespace base {
	class Event
	{
	public:
		Event() { }
		virtual ~Event() { }
	public:
		void wait() {
			_mutex.lock();
			_condition.wait(_mutex);
			_mutex.unlock();
		}
		void timed_wait(time_t sec) {
			_mutex.lock();
			_condition.timedwait(_mutex, sec);
			_mutex.unlock();
		}
		void notify_one() {
			_condition.signal();
		}
		void notify_all() {
			_condition.broadcast();
		}
	private:
		Mutex _mutex;
		Cond _condition;
	};

	template <typename T>
	class Queue : public std::deque<T>
	{
	public:
		Queue() { }
		virtual ~Queue() { }
	public:
		void push(T& t) {
			_mutex.lock();
			std::deque<T>::push_back(t);
			_mutex.unlock();
		}
		
		bool get(T& t) {
			_mutex.lock();
			if (!std::deque<T>::empty()) {
				t = std::deque<T>::front();
				std::deque<T>::pop_front();
				_mutex.unlock();
				return true;
			}
			_mutex.unlock();
			return false;
		}
		
		void clear() {
			_mutex.lock();
			std::deque<T>::clear();
			_mutex.unlock();
		}
	private:
		Mutex _mutex;
	};

	template <typename T>
	class DataHandler : public IRunnable
	{
	public:
		DataHandler() { Start(); }
		virtual ~DataHandler() { Stop(); }
	public:
		// signal notify
		void NotifyOne() {
			_event.notify_one();
		}
		// notify all
		void NotifyAll() {
			_event.notify_all();
		}

		// push data
		void Put(T& t) {
			_record_set.push(t);
			// send notify signal
			_event.notify_one();
		}

		size_t BufferSize() {
			return _record_set.size();
		}

		void Stop() {
			_running = false;
			_event.notify_one();
			_thread.join();
		}
		
		virtual void run() {
			while (_running) {
				_event.wait();
				while (!_record_set.empty()) {
					T t;
					if (_record_set.get(t)) {
						DataFunc(t);
					}
				} // while
			} // while
		}

		/**
		 * TODO::implement this func on sub-class
		 */
		virtual void DataFunc(T& t) {}
		
	private:
		void Start() {
			_running = true;
			_thread.set_func(this);
			_thread.start();
		}
	protected:
		Queue<T> _record_set;	/**< stream data record set */
		Event _event;			/**< signal */
		bool _running;
		Thread _thread;
	};
}

#endif /* _DATAHANDLER_H_ */
