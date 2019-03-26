module Util
  module ClassDecorations
    def make_safe!(name)
      unsafe = instance_method(:"#{name}!")
      define_method name do
        unsafe
      end
    end

    def the_perfect_forwarding(name, pre_checks)
      old = instance_method(name)
      top_class = self
      define_method name do |*args, **opts|
        pre_checks.each(&:call)
        old.bind(self).call(*args, **opts) do |*bargs, **bopts|
          yield(*bargs, **bopts) if (bargs&.empty? == false) || (bopts&.empty? == false)
        end
      end
    end

    def make_final(name)
      the_perfect_forwarding(
        name,
        -> (top_class) {
          if method(name).unbind != top_class.instance_method(name)
            raise "#{top_class} # #{name} is final -- overriden in #{self.class} (#{self.inspect})"
          end
        }
      )
    end
  end
end
