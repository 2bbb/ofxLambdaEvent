# ofxLambdaEvent

we don't want to do static_cast explicitly.

## Dependencies

* no dependency!

## What is this?

from:

```cpp
	ofAddListener(ofEvents().update, static_cast<void(*)(ofEventArgs &)>([](ofEventArgs &) {
		ofLogNotice() << "update!";
	}));
```

to:

```cpp
	ofAddLambdaListener(ofEvents().update, [](ofEventArgs &) {
		ofLogNotice() << "update!";
	});
```

## Notice

if use this, then we can't do `ofRemoveListener`.

therefore, i can't provide `ofRemoveLambdaListener`.

ofcourse, we can do as below:

```cpp
	std::function<void(ofEventArgs &)> callback;
	
	...
	
	callback = [](ofEventArgs &) {
		ofLogNotice() << "update!";
	};
	
	ofAddLambdaListener(ofEvents().update, callback);
	
	...
	
	ofRemoveListener(ofEvents().update, callback);
```

but, then we can use formal `ofAddListener`.

i have a idea that is dirty. but i think, we don't need function removes listener.

## Update history

### 2016/04/14 ver 0.0.1 release

## License

MIT License.

## Author

* ISHII 2bit [bufferRenaiss co., ltd.]
* ishii[at]buffer-renaiss.com

## At the last

Please create a new issue if there is a problem.
And please throw a pull request if you have a cool idea!!
