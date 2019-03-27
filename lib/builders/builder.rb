module Builders
  class Builder
    extend Base

    def initialize(workspace, scroll_name)
      @workspace = workspace
      @scroll_name = scroll_name
    end
  end
end
