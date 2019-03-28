module Cli
  module Queries
    class BuildId < Query
      def perform(_)
        require_relative '../../builders'
        ::Builders::Vagrant.gen_build_id
      end
    end
  end
end
