module Builders
  class Injector
    def initialize(workspace, scroll_name)
      @workspace = workspace
      @scroll_name = scroll_name
    end

    def inject(builder_def)
      Builders.each.reduce(builder_def) do |bdef, builder_pair|
        _, builder = builder_pair
        case bdef['type']
        when builder::TYPE
          builder
            .new(@workspace, @scroll_name)
            .inject(builder_def)
        else
          bdef # unchanged
        end
      end
    end
  end
end
