// Macros for defining type members
#define FAUX_ABSTRACT { throw ref new Platform::NotImplementedException("This method must be overridden by inheritors"); }

// Macros for defining events
#define DEFINE_ROUTED_EVENT(HandlerTypeNoHat, ArgsType, Name) private: \
	static Prose::Events::RoutedEvent^ _ ## Name ## Event; \
public: \
	static property Prose::Events::RoutedEvent^ Name ## Event { Prose::Events::RoutedEvent^ get() { return _ ## Name ## Event; } }; \
	virtual event HandlerTypeNoHat^ Name { \
		virtual Windows::Foundation::EventRegistrationToken add(HandlerTypeNoHat^ handler); \
		virtual void remove(Windows::Foundation::EventRegistrationToken token); \
		virtual void raise(Platform::Object^ sender, ArgsType args); \
	};

#define IMPLEMENT_ROUTED_EVENT(Owner, RoutingStrategy_, HandlerTypeNoHat, ArgsType, Name) Prose::Events::RoutedEvent^ Owner::_ ## Name ## Event = Prose::Events::EventManager::RegisterRoutedEvent( \
	#Name, Prose::Events::RoutingStrategy:: ## RoutingStrategy_, HandlerTypeNoHat::typeid, Owner::typeid); \
Windows::Foundation::EventRegistrationToken Owner::Name::add(HandlerTypeNoHat^ handler) { \
	return Prose::Events::EventManager::AddHandler(_ ## Name ## Event, this, ref new Windows::Foundation::TypedEventHandler<Platform::Object^, ICustomRoutedEventArgs^>([handler](Platform::Object^ sender, Prose::Events::ICustomRoutedEventArgs^ args) { \
		handler(sender, safe_cast<ArgsType>(args)); \
	}), false); \
} \
void Owner:: ## Name ## ::remove(Windows::Foundation::EventRegistrationToken token) { \
	Prose::Events::EventManager::RemoveHandler(_ ## Name ## Event, this, token); \
} \
void Owner:: ## Name ## ::raise(Platform::Object^ sender, ArgsType args) { \
	Prose::Events::EventManager::RaiseRoutedEvent(_ ## Name ## Event, this, args); \
}

// Macros for defining properties

#define DPHasLocalValue(Obj, Prop) ((Obj)->ReadLocalValue((Prop)) != Windows::UI::Xaml::DependencyProperty::UnsetValue)

#define LAZY_INIT(Ctor, Name) Name ? Name : (Name = ref new Ctor)

#define _CORE_DEPENDENCY_PROPERTY(Name) private: \
	static Windows::UI::Xaml::DependencyProperty^ _ ## Name ## Property; \
public: \
	static property Windows::UI::Xaml::DependencyProperty^ Name ## Property { Windows::UI::Xaml::DependencyProperty^ get() { return _ ## Name ## Property; } };	

#define DEPENDENCY_PROPERTY(Type, Name) _CORE_DEPENDENCY_PROPERTY(Name) \
	property Type Name { \
		virtual Type get() { return (Type)GetValue(Name ## Property); } \
		virtual void set(Type value) { SetValue(Name ## Property, value); } \
	}

#define DP_METADATA(DefaultValue) ref new Windows::UI::Xaml::PropertyMetadata(DefaultValue)
#define DP_METADATA_WITH_HANDLER(DefaultValue, ChangedHandler) ref new Windows::UI::Xaml::PropertyMetadata(DefaultValue, ref new Windows::UI::Xaml::PropertyChangedCallback(ChangedHandler))

#define _BACKING_FIELD(Type, Name) Type _ ## Name;
#define _NULLITY_FIELD_NAME(Name) _Is ## Name ## Set
#define _NULLITY_FIELD(Type, Name) bool _NULLITY_FIELD_NAME(Name);
#define _NULLITY_PROPERTY(Type, Name) property bool Is ## Name ## Set { bool get() { return _NULLITY_FIELD_NAME(Name); } };
#define _GETTER(Type, Name) Type get() { return _ ## Name; };
#define _SETTER(Type, Name) void set(Type value) { _ ## Name = value; };
#define _NOTIFY_PROPERTY_SETTER_BODY(Name) if(_ ## Name != value) { \
	_ ## Name = value; \
	OnPropertyChanged(L"Name"); \
}

#define PROPERTY(Type, Name) private: \
	_BACKING_FIELD(Type, Name) \
public: \
	property Type Name { \
		_GETTER(Type, Name) \
		_SETTER(Type, Name) \
	}

#define NOTIFY_PROPERTY(Type, Name) private: \
	_BACKING_FIELD(Type, Name) \
public: \
	property Type Name { \
		_GETTER(Type, Name) \
		void set(Type value) { \
			_NOTIFY_PROPERTY_SETTER_BODY(Name) \
		} \
	}

#define NOTIFY_NULLABLE_PROPERTY(Type, Name) private: \
	_BACKING_FIELD(Type, Name) \
	_NULLITY_FIELD(Type, Name) \
public: \
	property Type Name { \
		_GETTER(Type, Name) \
		void set(Type value) { \
			_NULLITY_FIELD_NAME(Name) = true; \
			_NOTIFY_PROPERTY_SETTER_BODY(Name) \
		} \
	} \
internal: \
	_NULLITY_PROPERTY(Type, Name)

#define NULLABLE_PROPERTY(Type, Name) private: \
	_BACKING_FIELD(Type, Name) \
	_NULLITY_FIELD(Type, Name) \
public: \
	property Type Name { \
		_GETTER(Type, Name) \
		void set(Type value) { \
			_NULLITY_FIELD_NAME(Name) = true; \
			_ ## Name = value; \
		} \
	}