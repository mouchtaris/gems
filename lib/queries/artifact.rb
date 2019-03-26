module Queries
  class Artifact
    def initialize(workspace)
      @workspace = workspace
    end

    def perform(opts)
      name = opts.scroll_name || (raise '--scroll is required')
      pp @workspace.scroll(name).packer_pure
    end
  end

  Queries.register Artifact
end
